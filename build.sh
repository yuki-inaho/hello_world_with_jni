javac -h . NativeClass.java 
g++ -std=c++11 -shared -fPIC -I$JAVA_HOME/include -I$JAVA_HOME/include/linux -L$JAVA_HOME/lib/server -ljvm NativeImpl.cpp -o libnative.so
java -Djava.library.path=. NativeClass