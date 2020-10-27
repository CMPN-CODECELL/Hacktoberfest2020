# Dockerizing Django Library App

## Run Web App with Simply Docker

Uncomment the line 8 in Dockerfile

```
    docker build -t django-docker:0.0.1 .
    docker run -p 8000:8000 django-docker:0.0.1 
```

Go to browser and check server is running on localhost:8000 or 0.0.0.0:8000

## Dockerize with Docker Compose

```
    docker-compose up
```

Go to browser and check server is running on 0.0.0.0:8000

