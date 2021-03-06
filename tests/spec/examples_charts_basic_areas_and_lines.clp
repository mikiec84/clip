(set height 480px)
(set width 1200px)

(plot
    axes (bottom top)
    limit-y (-50 50)
    areas (
        data-x (csv "tests/testdata/areadata2.csv" x)
        data-y (csv "tests/testdata/areadata2.csv" z)
        data-y-low (csv "tests/testdata/areadata2.csv" y)
        color #ccc)
    areas (
        data-x (csv "tests/testdata/areadata2.csv" x)
        data-y (csv "tests/testdata/areadata2.csv" z2)
        data-y-low (csv "tests/testdata/areadata2.csv" y2)
        color #888)
    lines (
        data-x (10 20 30 40 50)
        data-y (1.23 10.32 -6.23 4.43 3.45)
        marker-size 3pt)
    legend-overlay (
        position (bottom right)
        item-flow on
        item (label "Series A" color #ccc)
        item (label "Series B" color #888)
        item (label "Combined" color #000)))

