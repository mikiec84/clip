(set height 480px)
(set width 1200px)

(chart/linechart
    data-x (csv "tests/testdata/city_temperatures_london.csv" month)
    data-y (csv "tests/testdata/city_temperatures_london.csv" temperature)
    labels (csv "tests/testdata/city_temperatures_london.csv" temperature_str)
    scale-x-padding 0.6
    limit-y (-10 32)
    axes (bottom left)
    axis-x-label-placement (linear-alignat 1 1)
    axis-x-label-format (custom "Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec")
    axis-y-label-placement (linear-alignat 5 -10)
    color #06c
    marker-size 3pt
    legend-overlay (item (label "London" color #06c) position (bottom left)))
