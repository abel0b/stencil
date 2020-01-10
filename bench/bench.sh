[[ $debug = true ]] && set -x

versions="stencil-baseline stencil-seq stencil-simd stencil-openmp"
[[ $debug = true ]] && repeat=1 || repeat=10
plot_dir=plot
plot_width=1080
plot_height=720
output_dir=$source_dir/data/plot

mkdir -p $output_dir

echo "performing benchmarks .."

function plot_compare_makespan() {
    echo > $output_dir/compare_makespan.dat
    echo > $output_dir/compare_speedup.dat
    time_ms_ref=none
    for version in $versions
    do
        echo "$version"
        perf stat -o $version-perf-report.txt -ddd -r $repeat ./$version
        time_ms=$(cat $version-perf-report.txt | sed "s/^[ \t]*//" | grep "time elapsed" | cut -d" " -f1 | sed "s/,/\./")
        if [[ $time_ms_ref = none ]]
        then
            time_ms_ref=$time_ms
        fi
        version_name=$(echo $version | sed "s/stencil-//")
        speedup=$(echo "print($time_ms_ref/$time_ms)" | python3)
       echo "\"$version_name\" $time_ms" >> $output_dir/compare_makespan.dat
       echo "\"$version_name\" $speedup" >> $output_dir/compare_speedup.dat
    done


    echo > $output_dir/compare_makespan.conf
    echo "set terminal png size $plot_width,$plot_height" >> $output_dir/compare_makespan.conf
    echo "set output \"$output_dir/compare_makespan.png\"" >> $output_dir/compare_makespan.conf 
    echo "set xlabel \"version\"" >> $output_dir/compare_makespan.conf
    echo "set ylabel \"makespan (ms)\"" >> $output_dir/compare_makespan.conf
    echo "set boxwidth 0.5" >> $output_dir/compare_makespan.conf
    echo "set style fill solid" >> $output_dir/compare_makespan.conf
    echo "plot \"$output_dir/compare_makespan.dat\" using 2: xtic(1) with histogram" >> $output_dir/compare_makespan.conf
    
    cat $output_dir/compare_makespan.conf | gnuplot

    echo > $output_dir/compare_speedup.conf
    echo "set terminal png size $plot_width,$plot_height" >> $output_dir/compare_speedup.conf
    echo "set output \"$output_dir/compare_speedup.png\"" >> $output_dir/compare_speedup.conf 
    echo "set xlabel \"version\"" >> $output_dir/compare_speedup.conf
    echo "set ylabel \"speedup (ms)\"" >> $output_dir/compare_speedup.conf
    echo "set boxwidth 0.5" >> $output_dir/compare_speedup.conf
    echo "set style fill solid" >> $output_dir/compare_speedup.conf
    echo "plot \"$output_dir/compare_speedup.dat\" using 2: xtic(1) with histogram notitle" >> $output_dir/compare_speedup.conf
    
    cat $output_dir/compare_speedup.conf | gnuplot
}

plot_compare_makespan

