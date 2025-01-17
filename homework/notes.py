class Authorization:   # CLASS DEFINITION

    # __init__() always executed when class is being initiated
    def __init__(user, user_id, auth_level)   # VARIABLE / PARAMETER named user

        # use __init__ to assign values to object properties
        user.user_id = user_id   # PROPERTY named user.user_id
        user.auth_level = auth_level

    # __str__() controls what should be returned when class object is called as
    # a string
    def __str__(user):
        return f"{user.user_id}({user.auth_level})"

    # Objects can contain methods. These functions belong to the object.
    def myfunc(user):
        print("Hello, my name is " + user.user_id)

u1 = Authorization("Tervs", 1)   # OBJECT named u1

print(u1)   # Tervs(0)
print(u1.user_id)   # Tervs
print(u1.auth_level)   # 0

u1.auth_level = 0   # Modify PROPERTY
del u1.auth_level   # DELETE PROPERTY from OBJECT
del u1   # DELETE OBJECT

class Profile:
    pass   # CLASS DEFINITIONs cannot be empty; use PASS to avoid error

def get_authorization_level(one_id: Authorization):   # CLASS as a TYPE
    return one_id.auth_level   # one_id is an INSTANCE of CLASS Authorization

# DATA TYPES

# LIST: list = ["apple", "banana", "cherry", "melon"]
# LISTs are ordered, changable, and allow duplicate values
# LIST as a TYPE HINT, LIST have an INTERNAL TYPE
# The INTERNAL TYPE within square brackets are the TYPE PARAMETERS
# e.g. str is the TYPE PARAMETER passed to LIST
def process_user_ids(user_ids: list[str]):
    for user_id in user_ids:   # VARIABLE user_id is an element in user_ids
        print(user_id)

# TUPLE: tup = ("apple", "banana", "cherry", "melon")
# TUPLEs are ordered, unchangable, and allow duplicate values
# SET: set = {"apple", "banana", "cherry", "melon"}
# SETs are unordered, unchangeable*, and unindexed
# *SET items are unchangeable, but you can remove and add new items
def process_items(items_t: tuple[int, int, str], items_s: set[bytes]):
    return items_t, items_s

# DICTIONARY:   dict = {
#                   "brand": "Ford",
#                   "model": "Mustang",
#                   "year": 1964
#               }
# DICTIONARIES are ordered*, changeable, and do not allow duplicates
# *DICTIONARIES in Python 3.6 and earlier are unordered
# DICT must have 2 type PARAMETERS
# First PARAMETER for keys, second PARAMETER for values
def process_items(prices: dict[str, float]):   # prices is a DICT
    for item_name, item_price in prices.items():
        print(item_name)
        print(item_price)

# UNION: A VARIABLE can be any of several TYPES
# Python 3.8+
from typing import Union

def process_item(item: Union[int, str]):
    print(item)

# UNION:A VARIABLE can be declared to have several TYPES with |
# Python 3.10+
def process_item(item: int | str):   
    print(item)

# NONE: A VARIABLE can be declared to possibly have NO TYPE
# Python 3.6+
from typing import Optional

def say_hi(name: Optional[str] = None):
    if name is not None:
        print(f"Hey {name}!")
    else:
        print("Hello World!")

# Optional[Something] is actually a shortcut for Union[Something, None]
# Python 3.10+
def say_hi(name: str | None = None):
    if name is not None:
        print(f"Hey {name}!")
    else:
        print("Hello World")

# GENERIC TYPES: TYPEs that take TYPE PARAMETERS in square brackets

# PYDANTIC library to perform data validation
from datetime import datetime
from pydantic import BaseModel

class Profile(BaseModel):
    id: int
    name: str = "Tervs"
    signup_ts: datetime | None = None
    friends: list[int] = []

external_data = {
        "id": "123"
        "signup_ts": "2017-06-01 12:22",
        "friends": [1, "2", b"3"],
}
user = User(**external_data)
print(user)   # User id=123 name='John Doe' signup_ts=datetime.datetime(2017, 6, 1, 12, 22) friends=[1, 2, 3]
print(user.id)   # 123

# TYPE HINTs with metadata ANNOTATIONS
# Python 3.8+
from typing_extensions import Annotated   # installed with FastAPI

# Python 3.9+
from typing import Annotated   # now part of Python standard library

def say_hello(name: Annotated[str, "this is just metadata"]) -> str:
    return f"hello {name}"

# CREATING AND USING ENVIRONMENT VARIABLES IN THE SHELL (TERMINAL)
# Create environment variable MY_NAME

export MY_NAME="Trevor Freeman"
...
echo "Hello $MY_NAME"
> Hello Trevor Freeman

# READING ENV VARIABLES IN PYTHON
## main.py

import os

name = os.getenv("MY_NAME", "World")   # 2nd argument is a default return value
print(f"Hello {name} from Python")

# CREATE AN ENV VARIABLE FOR A SPECIFIC PROGRAM INVOCATION

MY_NAME="Trevor Freeman" python main.py
> Hello Trevor Freeman from Python

python main.py
> Hello World from Python

# Env variables can only handle text strings, so any value read in Python from
#    an env variable will be a string, and conversion to a different type or
#    any validation has to be done in code.
# PATH env variable is used by OS's to find programs to run
# PATH is one long string of directories separated by colons:
#     /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

# Let's say you install Python and it ends up in /opt/custompython/bin
# If you say yes to update the PATH env variable, then /opt/custompython/bin
#    will be added to the PATH env variable:
#    /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/custompython/bin

# A VIRTUAL ENVIRONMENT IS A DIRECTORY WITH SOME FILES IN IT THAT ISOLATES
#    PACKAGES FROM THE REST OF YOUR SYSTEM
# Create a directory for your project: ./project
# Create directory for environment files: ./project/env
# Create virtual environment while in project directory (only do this once):
python3 -m venv env

# Activate virtual environment (every new sessions):
source ./env/bin/activate

# Check which virtual env is active (optional):
which python   # if it shows 'env/bin/python', then it worked

# Upgrade pip (normally once, after first creating virtual env)
python -m pip install --upgrade pip

# Add a .gitignore file to exclude everything in /env from git
echo "*" > ./env/.gitignore

# Installing packages after activating virtual environment
pip install "fastapi[standard]"

# It's a very good idea to put packages and versions your program needs in a
#    file (e.g. requirements.txt, or pyproject.toml)
# Installing from "requirements.txt"
pip install -r requirements.txt

# Deactivating the virtual env
deactivate

# INSTALLING SERVER
pip install "fastapi[standard]"

# ASYNCHRONOUS CODE: Tells computer/program that at some point in the code,
#    it will have to wait for something else to finish somewhere else.
# If execution time is spent waiting for I/O operations, they call them
#    "I/O bound" operations.
# SEQUENTIAL CODE: The computer/program follows all steps in sequence before
#    switching to a different task, even if it involves waiting.
# ASYNCHRONOUS CODE is sometimes called CONCURRENCY. It is different from
#    PARALLELISM.
# Both relate to "different things happening more or less at the same time."
# When most execution time is spent doing work (not waiting), and the work is
#    done by a CPU, they call these problems "CPU bound."
# PARALLELISM can be used to cut down the execution time of CPU bound code
# Common CPU bound operations: Audio/Image processing, Computer vision, Machine
#    learning, Deep learning

# ASYNC and AWAIT: burgers = await get_burgers(2)
# While get_burgers(2) is processing, Python can go and do something else.
# AWAIT needs to be inside an asynchronous function.

async def get_burgers(number: int):
    # Do some asynchronous stuff to create the burgers
    return burgers

# This is NOT asynchronous

def get_sequential_burgers(number: int):
    # Do some sequential stuff to create the burgers
    return burgers

# When you call 'async def', you have to 'await' it. So, this won't work:
burgers = get_burgers(2)

## FastAPI

from fastapi import FastAPI

app = FastAPI()   # Create a FastAPI "INSTANCE" variable named app
                  # FastAPI() is a class

@app.get("/")
async def root():
    return {"message": "Hello World"}

## PATH
# Refers to last part of URL starting from the first /, so in 
#    'https://example.com/items/foo', the path would be '/items/foo'
# PATH = ENDPOINT = ROUTE
# PATH is the main way to separate "concerns" and "resources"

## OPERATION
# Refers to one of the HTTP "methods": POST, GET, PUT, DELETE, OPTIONS, HEAD,
#    PATCH, TRACE
# POST = create data. GET = read data. PUT = update data. DELETE = delete data

## PATH OPERATION DECORATOR
# @app.get("/") tells FastAPI that the next function below will handle requests
#    that go to the path "/" using a 'GET' operation
# @app.post() @app.put() @app.delete() @app.options() @app.head() @app.patch()
#    @app.trace()
# FastAPI doesn't enforce any specific meaning to each operation, this
#    information is just a guideline (e.g. GraphQL uses only POST operations)

## PATH OPERATION FUNCTION
# The PATH OPERATION FUNCTION is the FUNCTION that appears on the next line
#    after @decorator line.
# You must create a PATH OPERATION FUNCTION that uses 'await' with 'async def'

@app.get('/burgers')
async def read_burgers():
    burgers = await get_burgers(2)
    return burgers

# Functions defined with 'async def' have to be 'awaited'. So functions with
#    'async def' can only be called inside of functions also defined with
#    'async def'. ***So how do you call the first async function?***
# In FastAPI, the 'first' async function is always the PATH OPERATION FUNCTION.
# ASYNC and AWAIT are relatively new; previously asynchronous code was handled
#    with threads.
# Modern versions of Python support Asynchronous code using COROUTINEs with
#    async and await syntax

# STARTING SERVER
# Normally you can start the server with
fastapi dev main.py
# or
uvicorn main:app --reload

# If starting the server from a VIRTUAL ENVIRONMENT
uvicorn main:app --host 0.0.0.0 --port 8000 --reload
# then access website at http://<your-ip>:8000

## FastAPI - PATH PARAMETERS
# Order of PATH OPERATIONS matters

...
@app.get("/users/me")
async def read_user_me():
    return {"user_id": "the current user"}

@app.get("/users/{user_id}")   # {user_id} = parameter / variable
async def read_user(user_id: str):    # {user_id} passed to user_id
    return {"user_id": user_id}
...

# If you go to <your-ip>:8000/users/me, you would see {"user_id":"me"}
# If /users/{user_id} was placed first, it would also match /users/me, executing
#    "async def read_user(user_id: str):" instead of "async def read_user_me():"
# Similarly, you cannot redefine a path, as the first path will always be used

## PREDEFINED VALUES
# If you have a PATH OPERATION that receives a PATH PARAMETER, but you want the
#    PATH PARAMETER values to be predefined, you can use Python ENUM
# Import Enum, then create a sub-CLASS that INHERITs from str and Enum
# Then create CLASS ATTRIBUTES with fixed values
# After, create a PATH PARAMETER w/ a TYPE ANNOTATION using the CLASS you made

from enum import Enum
from fastapi import FastAPI


class ModelName(str, Enum):
    alexnet = "alexnet"
    resnet = "resnet"
    lenet = "lenet"


app = FastAPI()


@app.get("/models/{model_name}")
async def get_model(model_name: ModelName):
    if model_name is ModelName.alexnet:
        return {"model_name": model_name, "message": "Deep Learning FTW!"}

    if model_name.value == "lenet":
        return {"model_name": model_name, "message": "LeCNN all the images"}

    return {"model_name": model_name, "message": "Have some residuals"}
