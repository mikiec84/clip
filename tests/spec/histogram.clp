(set width 480px)
(set height 380px)

(plot
    limit-x (0 7)
    limit-y (0 10000)
    scale-y (log)
    axes (left bottom)
    axis-x-label-placement (linear-interval 1 1 6)
    bars (
      data-x (csv "tests/testdata/histogram.csv" var0)
      data-y (csv "tests/testdata/histogram.csv" var1)
      bar-width (1.8em)
      color #666))
