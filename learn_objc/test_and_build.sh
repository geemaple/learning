while true; do
    read -p "run unit test [Y|N] ?" yn
    case $yn in
        [Yy]* ) xcodebuild -project learn_objc.xcodeproj -scheme unit_test test; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
done


while true; do
    read -p "build all target [Y|N] ?" yn
    case $yn in
        [Yy]* ) xcodebuild -project learn_objc.xcodeproj -alltargets; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
done


