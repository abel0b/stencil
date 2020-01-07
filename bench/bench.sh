versions="stencil-baseline"
repeat=10

echo "performing becnhmarks .."

for version in $versions
do
    perf stat -ddd -r $repeat ./$version
done

