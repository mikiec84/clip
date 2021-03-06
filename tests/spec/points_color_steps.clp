(chart/scatterplot
    data-x (csv tests/testdata/gauss3d.csv x)
    data-y (csv tests/testdata/gauss3d.csv y)
    data-color (csv tests/testdata/gauss3d.csv z)
    limit-x (0 400)
    limit-y (0 200)
    color-map (steps (0 #f00) (0.2 #0f0) (0.4 #00f) (0.6 #0f0) (0.8 #f00) (1.0 #00f))
    axis-y-label-placement (subdivide 5)
    axes (bottom left)
    grid (color #fff)
    background #eee
    border none)
