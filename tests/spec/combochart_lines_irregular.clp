(set height 480px)
(set width 1200px)

(plot
    limit-x (-12 22)
    limit-y (-35 55)
    axes (bottom left)
    lines (
        data-x (csv "tests/testdata/irregular_data1.csv" x)
        data-y (csv "tests/testdata/irregular_data1.csv" y)
        color #06c
        marker-size 3pt)
    lines (
        data-x (csv "tests/testdata/irregular_data2.csv" x)
        data-y (csv "tests/testdata/irregular_data2.csv" y)
        color #c06
        marker-size 3pt)
    legend-overlay (
        position (bottom left)
        background #fff
        item (label "Series A" color #ccc)
        item (label "Series B" color #888)))
