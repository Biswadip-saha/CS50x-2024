import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    id = session["user_id"]
    username = db.execute(
        "SELECT * FROM users WHERE id = ?", id)[0]["username"]
    stocks = db.execute("SELECT * FROM persons WHERE username = ?", username)
    balance = db.execute("SELECT * FROM users WHERE id = ?", id)[0]["cash"]
    currprice = []
    value = []
    total = 0
    for i in stocks:
        symbol = i["symbol"]
        currprice.append(lookup(symbol)["price"])
        value.append((lookup(symbol)["price"]*i["shares"]))
        total = total + (lookup(symbol)["price"]*i["shares"])
    return render_template("index.html", stocks=stocks, currprice=currprice, value=value, total=total, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Insert valid input for shares")
        if shares <= 0:
            return apology("Insert valid input for shares")
        elif lookup(symbol) == None:
            return apology("No such symbol exist")
        else:
            id = session["user_id"]
            cash = db.execute(
                "SELECT * FROM users WHERE id = ?", id)[0]["cash"]
            username = db.execute(
                "SELECT * FROM users WHERE id = ?", id)[0]["username"]
            price = lookup(symbol)["price"]*shares
            result = db.execute(
                "SELECT * FROM persons WHERE symbol = ?", symbol)
            if result:
                prevshares = result[0]["shares"]
            else:
                prevshares = 0
            if (cash < price):
                return apology("You don't have enough cash")
            else:
                if len(db.execute("SELECT * FROM persons WHERE symbol = ? AND username = ?", symbol, username)) == 0:
                    db.execute(
                        "INSERT INTO persons(username, symbol, shares) values(?, ?, ?)", username, symbol, shares)
                else:
                    db.execute(
                        "UPDATE persons SET shares = ? WHERE username = ?", shares + prevshares, username)
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           cash - price, id)
                method = 'Bought'
                db.execute("INSERT INTO history(username, symbol, shares, method, value) VALUES(?, ?, ?, ?, ?)",
                           username, symbol, shares, method, price)
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session["user_id"]
    username = db.execute(
        "SELECT * FROM users WHERE id = ?", id)[0]["username"]
    stocks = db.execute("SELECT * FROM history WHERE username = ?", username)
    return render_template("history.html", stocks=stocks)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("No as such symbol exist.")
        else:
            return render_template("quoteinfo.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure password and confirm password are equal
        elif (request.form.get("password") != request.form.get("confirmation")):
            return apology("passowrd and confirm password don't match")

        # Ensure username is not taken
        elif (len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) > 0):
            return apology("username already exist")

        else:
            # Query Database for register
            username = request.form.get("username")
            password = request.form.get("password")
            hash = generate_password_hash(password)
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

            # Remember which user has logged in
            session["user_id"] = db.execute(
                "SELECT * FROM users WHERE username = ?", username)[0]["id"]

            # Redirect user to home page
            return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session["user_id"]
    username = db.execute(
        "SELECT * FROM users WHERE id = ?", id)[0]["username"]
    if request.method == "GET":
        stocksinfo = []
        values = db.execute(
            "SELECT * FROM persons WHERE username = ?", username)
        counter = 0
        for i in values:
            stocksinfo.append(values[counter]["symbol"])
            counter = counter + 1
        return render_template("sell.html", stocksinfo=stocksinfo)
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol == None:
            return apology("Please Select a valid symbol")
        cash = db.execute("SELECT * FROM users WHERE id = ?", id)[0]["cash"]
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Insert valid input for shares")
        if shares <= 0:
            return apology("Insert valid input for shares")
        elif lookup(symbol) == None:
            return apology("No such symbol exist")
        else:
            quote = db.execute(
                "SELECT * FROM persons WHERE username = ? AND symbol = ?", username, symbol)
            if len(quote) == 0:
                return apology("You don't own such Stocks")
            else:
                method = 'Sold'
                value = lookup(symbol)["price"]*shares
                holding = quote[0]["shares"]
                if holding < shares:
                    return apology("You don't have that many shares")
                elif holding == shares:
                    db.execute(
                        "DELETE FROM persons WHERE username = ? AND symbol = ?", username, symbol)
                else:
                    db.execute("UPDATE persons SET shares = ? WHERE username = ? AND symbol = ?",
                               holding - shares, username, symbol)
                db.execute(
                    "UPDATE users SET cash = ? WHERE username = ?", cash + value, username)
                db.execute("INSERT INTO history (username, symbol, shares, method, value) VALUES(?, ?, ?, ?, ?)",
                           username, symbol, shares, method, value)
                return redirect("/")
