(set height 480px)
(set width 1200px)

(plot
    axes (bottom left)
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
    legend-overlay (
        position (bottom left)
        background #fff
        item (label "Series A" color #ccc)
        item (label "Series B" color #888)))
