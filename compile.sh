clear
if [[ $1 == "re" ]]
then
    echo "------------RE-BUILD"------------
    if [ -d "./build/" ]
    then
        rm -rf ./build/ ./zappy_*
        rm -f ./ECS/ECS.a ./ECS/default.so
        rm -f ./gui/plugins/*.so
    fi
    mkdir ./build/ && cd ./build/
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    cd ..
    echo "------------END------------"

elif [[ $1 == "d" ]]
then
    echo ""------------DEBUG"------------"
    if [ -d "./build/" ]
    then
        rm -rf ./build/ ./zappy_*
        rm -f ./ECS/ECS.a ./ECS/default.so
        rm -f ./gui/plugins/*.so
    fi
    mkdir ./build/ && cd ./build/
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
    cmake --build . -v
    cd ..
    echo "------------END------------"

elif [[ $1 == "c" ]]
then
    echo "------------CLEAR------------"
    rm -rf ./build/ ./zappy_*
    rm -f ./ECS/ECS.a ./ECS/default.so
    rm -f ./gui/plugins/*.so
    echo "------------END------------"

else
    echo "------------BUILD------------"
    if [ ! -d "./build/" ]
    then
        mkdir ./build/ && cd ./build/
        cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
        cd ..
        cmake --build ./build/
    else
        cmake --build ./build/
    fi
    echo "------------END------------"
fi
