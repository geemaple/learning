
pintos_path="$HOME/Developer/learning/learn_cs/cs162_operating_system/pintos"
git submodule update --init pintos
docker run -it --rm --name pintos --mount type=bind,source=$pintos_path,target=/home/PKUOS/pintos pkuflyingpig/pintos bash