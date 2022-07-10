echo "Animating..."
convert -delay 15 -loop 0 `find $PWD/figures/ -type f | sort -V` animation.gif
echo "Animation done."
