(TeX-add-style-hook "SwagwayRapport"
 (lambda ()
    (LaTeX-add-bibliographies
     "bib")
    (LaTeX-add-labels
     "chap:ind"
     "chap:kon")
    (TeX-add-symbols
     "authorvar"
     "pretitlevar"
     "titlevar"
     "subtitlevar"
     "datevar"
     "subjectvar"
     "classvar"
     "teachervar")
    (TeX-run-style-hooks
     "fixme"
     "margin"
     "verbatim"
     "microtype"
     "tikz"
     "url"
     "unicode-math"
     "amsmath"
     "babel"
     "latex2e"
     "memoir10"
     "memoir"
     "a4paper"
     "oneside"
     "article"
     "danish"
     "table"
     "draft")))

