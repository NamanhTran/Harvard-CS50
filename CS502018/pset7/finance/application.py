import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Ensure environment variable is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Create holdings table if not created
    db.execute("CREATE TABLE IF NOT EXISTS holdings (id INTEGER NOT NULL, stock TEXT NOT NULL, amount INEGER NOT NULL)")

    # Gets the symbols and stock amount from the holdings tables
    rows = db.execute("SELECT SUM(amount), stock FROM holdings WHERE id=:id GROUP BY stock", id=session["user_id"])

    # Gets the cash from the user from the users table
    balance = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

    # Declare a list for price
    price = []

    # Puts each stock info into price so the price of each stock is updated
    for row in range(len(rows)):
        price.append(lookup(rows[row]["stock"]))

    # Send the user their index
    return render_template("index.html", rows=rows, price=price, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # If user sent infomation back
    if request.method == "POST":

        # Gets the stock information
        stock_info = lookup(request.form.get("symbol"))

        # If nothing is returned by the stock function return an error
        if stock_info == None:
            return apology("Stock is invalid", 400)

        # Gets the shares in that the user summited
        shares = request.form.get("shares")

        # Ensures that the shares are positive, whole numbers
        if not shares.isdigit() or float(shares) < 1 or not float(shares).is_integer():
            return apology("Please enter a positive, whole number amount of stocks", 400)

        else:
            # Gets the user's row info from users table
            row = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])
            cash = row[0]["cash"]

            # Create history table if not created
            db.execute("CREATE TABLE IF NOT EXISTS history (id INTEGER NOT NULL, stock TEXT NOT NULL, action TEXT NOT NULL, amount INTEGER NOT NULL, balance INTEGER NOT NULL, date DATETIME NOT NULL)")

            # Figure out how much money the user has left
            cash -= stock_info["price"] * int(request.form.get("shares"))

            # Update the user's cash
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=cash, id=row[0]["id"])

            # Update history table and holdings table
            db.execute("INSERT INTO history (id, stock, action, amount, balance, date) VALUES(:id, :stock, :action, :amount, :balance, date('now'))",
                        id=session["user_id"], stock=stock_info["symbol"], action="BUY", amount=request.form.get("shares"), balance=cash)

            # Test will be use to see if a stock exists on the holdings table
            test = db.execute("SELECT * FROM holdings WHERE id=:id AND stock=:stock",
                              id=session["user_id"], stock=stock_info["symbol"])

            # If certain stock is not in the holdings table
            if len(test) != 1:
                # Then insert into the table
                db.execute("INSERT INTO holdings (id, stock, amount) VALUES(:id, :stock, :amount)",
                            id=session["user_id"], stock=stock_info["symbol"], amount=int(request.form.get("shares")))

            # If certain stock already exist in the table
            else:
                # Then just update the amount row
                db.execute("UPDATE holdings SET amount=amount + :shares WHERE id=:id AND stock=:stock",
                           shares=int(request.form.get("shares")), id=session["user_id"], stock=stock_info["symbol"])

            # Send user back to index
            return redirect("/")

    else:
        # Sends the buy.html to the user
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Rows will hold everything that the user did
    rows = db.execute("SELECT * FROM history WHERE id=:id", id=session["user_id"])

    # Return the history.html page
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # If user sent back data
    if request.method == "POST":
        # Get the stock info
        temp = lookup(request.form.get("symbol"))

        # If stock symbol does exist
        if temp != None:
            # Return the stock info to the user
            return render_template("quoted.html", temp=temp)

        else:
            # If stock does not exist return an error
            return apology("Stock given is not valid", 400)

    else:
        # Send the user the quote.html
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("please confirm password", 400)

        # Ensure that password and confirmation match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Password does not match", 400)

        else:
            # Checks if the username already exists in the database
            rows = db.execute("SELECT * FROM users")
            for row in rows:
                if row["username"] == request.form.get("username"):
                    return apology("Someone else has taken that username", 400)

            # Hashes the password
            hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

            # Stores both the hashed password and usernames in the table
            db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                       username=request.form.get("username"), hash=hash)

            # Redirect user to login page
            return redirect("/login")

    else:
        # Send the user the register.html page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Gets the user's stock info from holdings table
    rows = db.execute("SELECT * FROM holdings WHERE id=:id", id=session["user_id"])

    # If user sent back infomation
    if request.method == "POST":

        # Ensure that the user did input a symbol
        if request.form.get("symbol") == "":
            return apology("Please choose a stock to sell", 400)

        # Ensures that the user picked a stock to sell
        elif request.form.get("shares") == None:
            return apology("Please choose amount of stock to sell", 400)

        # If user's input is all good
        else:
            # Checks if the user has that many stocks that they want to sell
            check = db.execute("SELECT * FROM holdings WHERE id=:id AND stock=:stock",
                                id=session["user_id"], stock=request.form.get("symbol"))
            if check[0]["amount"] < int(request.form.get("shares")):
                # Return error if user tried to sell more than they have
                return apology("You don't own that many stocks", 400)

            else:
                # Get cash from users table
                cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
                cash = cash[0]["cash"]

                # Update the holdings table subtracting the amount of stocks
                db.execute("UPDATE holdings SET amount=amount - :shares WHERE id=:id AND stock=:stock",
                            shares=int(request.form.get("shares")), id=session["user_id"], stock=request.form.get("symbol"))

                # Get stock information
                stock_info = lookup(request.form.get("symbol"))

                # Add stock's price to the user's total cash
                cash += stock_info["price"] * int(request.form.get("shares"))

                # Update the cash in the users table
                db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash, id=session["user_id"])

                # Insert a row into history table recording that the stock was sold
                db.execute("INSERT INTO history (id, stock, action, amount, balance, date) VALUES(:id, :stock, :action, :amount, :balance, date('now'))",
                            id=session["user_id"], stock=stock_info["symbol"], action="SELL", amount=request.form.get("shares"), balance=cash)

                # Check is used to check if the amount of stocks in the holding is 0
                check = db.execute("SELECT * FROM holdings WHERE id=:id AND stock=:stock",
                                   id=session["user_id"], stock=request.form.get("symbol"))

                # If amount of stock is 0 then delete the row from the holdings table
                if check[0]["amount"] == 0:
                    db.execute("DELETE from holdings WHERE id=:id and stock=:stock",
                               id=session["user_id"], stock=request.form.get("symbol"))

            # Redirect user to the root page
            return redirect("/")

    else:
        # Send the user the sell.html
        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
