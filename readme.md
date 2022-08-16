## Dockerbuild

# Building the dockerimage
docker build -t worksheet_crafter_oszimilian .

docker build --no-cache -t worksheet_crafter_oszimilian .

# Execute the dockerimage with a bind mount
docker run -v D:\14_Docker:/home/maximilian/Data worksheet_crafter_oszimilian
