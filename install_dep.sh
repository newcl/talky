wget http://downloads.sourceforge.net/project/boost/boost/1.57.0/boost_1_57_0.tar.bz2?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.57.0%2F&ts=1460703658&use_mirror=iweb
boost_1_57_0.tar.bz2
tar --bzip2 -xf boost_1_57_0.tar.bz2
cd boost_1_57_0
./bootstrap.sh
./b2 install
cd -