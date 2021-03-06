(set width 2048px)
(set height 1024px)
(set dpi 240)
(set font "Latin Modern Roman")

(plot
  limit-y (0 1000)
  limit-x (0 1000)
  scale-y (logarithmic)
  errorbars (
      data-x (csv "tests/testdata/errorbars.csv" "x")
      data-y-low (csv "tests/testdata/errorbars.csv" "y_min")
      data-y-high (csv "tests/testdata/errorbars.csv" "y_max"))
  points (
      data-x (csv "tests/testdata/errorbars.csv" "x")
      data-y (csv "tests/testdata/errorbars.csv" "y"))
  legend-overlay (
      item (label "Random Data")))
