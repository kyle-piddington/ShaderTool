sh install_dependencies.sh
if [ ! -d _build ]; then
	mkdir _build
fi

cd _build
cmake .. && make
