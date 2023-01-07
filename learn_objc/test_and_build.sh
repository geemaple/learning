while true; do
    read -p "run unit test ?" yn
    case $yn in
        [Yy]* ) xcodebuild -project learn_objc.xcodeproj -scheme unit_test test; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
done

xcodebuild -project learn_objc.xcodeproj -alltargets
