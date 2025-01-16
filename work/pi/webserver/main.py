from fastapi import FastAPI

app = FastAPI()   # app variable "instance" of the class 'FastAPI'

@app.get("/")   # path operation: @decorator: uses function below it along with
                # current line here it says 'async def root():' corresponds to
                # path "/" with operation 'get', i.e. path operation decorator

async def root():   # path operation function: it will be called by FastAPI
                    # whenever it receives a request to the URL "/" using
                    # a GET operation. Can also be a normal function
                    # 'def root():'

    return {"message": "Welcome to the Pi-Server API!"}   # return the content
