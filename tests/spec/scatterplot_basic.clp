(chart/scatterplot
    data-x (csv tests/testdata/gauss2d.csv x)
    data-y (csv tests/testdata/gauss2d.csv y)
    axes (bottom left)
    axis-y-label-placement (subdivide 5)
    grid (color #fff)
    legend-overlay (item (label "Random Data"))
    background #eee
    border none
    limit-x-min 0
    limit-x-max 400
    limit-y-min 0
    limit-y-max 200)
