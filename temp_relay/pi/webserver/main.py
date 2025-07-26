#from fastapi import FastAPI

#app = FastAPI()   # app variable "instance" of the class 'FastAPI'

#@app.get("/")   # path operation: @decorator: uses function below it along with
                # current line here it says 'async def root():' corresponds to
                # path "/" with operation 'get', i.e. path operation decorator
#async def root():   # path operation function: it will be called by FastAPI
                    # whenever it receives a request to the URL "/" using
                    # a GET operation. Can also be a normal function
                    # 'def root():'
    #return {"message": "Welcome to the Pi-Server API!"}   # return the content

#from fastapi import FastAPI

#app = FastAPI()   # app variable "instance" of the class 'FastAPI'

#@app.get("/items/{item_id}")   # {item_id} = whatever you append to url path
    #async def read_item(item_id: int):   # read_item(item_id):
    #return {"item_id": item_id}

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
