[[ $debug = true ]] && set -x

versions="stencil-baseline stencil-openmp"
[[ $debug = true ]] && repeat=1 || repeat=10
plot_dir=plot
plot_width=1080
plot_height=720
output_dir=$source_dir/data/plot

mkdir -p $output_dir

echo "performing benchmarks .."

function plot_compare_makespan() {
    echo > $output_dir/compare_makespan.dat
    for version in $versions
    do
        perf stat -o $version-perf-report.txt -ddd -x "," -r $repeat ./$version
        time_ms=$(cat $version-perf-report.txt | grep task-clock | cut -d, -f1)
       echo "\"$version\" $time_ms" >> $output_dir/compare_makespan.dat
    done


    echo > $output_dir/compare_makespan.conf
    echo "set terminal png size $plot_width,$plot_height"
    echo "set output \"$output_dir/compare_makespan.png\""
    echo "set xlabel \"version\""
    echo "set ylabel \"makespan (ms)\""
    echo "set boxwidth 0.5"
    echo "set style fill solid"
    echo "plot \"$output_dir/compare_makespan.dat\" using 2: xtic(1) with histogram"
    
    cat $output_dir/compare_makespan.conf | gnuplot
}

plot_compare_makespan

