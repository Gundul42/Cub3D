COMPILER="gcc"
TOOL1="build-essential"
TOOL2="libbsd-dev"
TOOL3="libx11-dev"
TOOL4="libxext-dev"
MAKE="make"

echo ">>> Installing prerequisites to be able to compile the project"
echo ">>> We will need:"
echo 
echo ">>> "$COMPILER $TOOL1 $TOOL2 $TOOL3 $TOOL4 $MAKE
echo
echo "Please grant sudo access to be able to check and install"
echo "missing dependencies"
echo
if [ ! -f 'sudo apt update && install -y $COMPILER $TOOL1 $TOOL2 $TOOL3 $TOOL4 $MAKE' ]; then
		echo ">>> SUCCESS: type 'make' or 'make bonus' to compile"
else
		echo "Something went wrong"
fi
