(plot
  axis-bottom (
    limit (0 100))
  lines (
        data-x (csv "tests/testdata/measurement.csv" time)
        data-y (csv "tests/testdata/measurement.csv" value2)
        color #000))
