#set document(
  title: "DS I Projekt - Meteorologické stanice",
  author: "Roman Táborský (TAB0042)",
  date: auto,
)

#set page(
  paper: "a4",
  margin: (x: 2.5cm, y: 2.5cm),
)

#set par(justify: true)

#set text(
  font: "Roboto Slab",
  lang: "cs",
  size: 11pt,
)
#show raw: set text(font: "Roboto Slab")

#set heading(numbering: "1.")
#show heading.where(level: 1): set block(below: 2em)
#show heading.where(level: 2): set block(below: 1em)


#image("obrázky/logo.png")
#align(horizon + center)[
  #text(size: 15pt)[Projekt do předmětu Databázové systémy I]

  #text(size: 20pt)[*Jméno projektu*]

  #text(size: 12pt, weight: "light")[(c) 2012-2023, verze 1.0, #datetime.today().display()]
  #v(10pt);
  #text(size: 14pt, weight: "light")[
    #show par: set block(below: .8em)
    Jméno příjmení

    Katedra informatiky

    `http://dbedu.cs.vsb.cz/`
  ]
]
#pagebreak()

// update page numbering
#set page(numbering: "1")

#outline()
#pagebreak()

// set paragraph breaks
#show par: set block(below: 1.3em)

= Specifikace zadání

== Motivace
