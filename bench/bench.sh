[[ $debug = true ]] && set -x

versions="stencil-baseline stencil-openmp"
[[ $debug = true ]] && repeat=1 || repeat=10
plot_dir=plot
plot_width=1080
plot_height=720

mkdir -p plot

echo "performing benchmarks .."


function plot_compare_versions_dat() {
    echo > compare_versions.dat
    for version in $versions
do
        perf stat -o $version-perf-report.txt -ddd -x "," -r $repeat ./$version
        time_ms=$(cat $version-perf-report.txt | grep task-clock | cut -d, -f1)
       echo "\"$version\" $time_ms" >> compare_versions.dat
    done
}

function plot_compare_versions_conf {
    echo "set terminal png size $plot_width,$plot_height"
    echo "set output \"compare_versions.png\""
    echo "set xlabel \"version\""
    echo "set ylabel \"makespan (ms)\""
    echo "set boxwidth 0.5"
    echo "set style fill solid"
    echo "plot \"compare_versions.dat\" using 2: xtic(1) with histogram"
}

plot_compare_versions_dat
plot_compare_versions_conf > compare_versions.conf
cat compare_versions.conf | gnuplot
