# 7:15
1. tlusty vs tenky,http vs https
- Tlustý (thick, fat): aplikace u klienta, takže server chilluje, funguje i offline.
- Tenky (thin): u klienta jen basic rozhrání na hardwaru, logika a vše pro appku je na serveru. Menší náklady a lepší bezpečnost. Např. vzdálená plocha.

2. css button co ma highlight ma mit zluty background a tucny text
.highlight {
  background-color: yellow;
  font-weight: bold;
}


.highlight {
  font-weight: bold;
  background-color: yellow;
}

3. min 5 html5 elementů
nav, svg, picture, video, audio, canvas

4. Kdyz kliknes na tlacitko, tak se ti vytori span s classou box
document.querrySelector('button').addEventListener('click', function(){
  var span = document.createElement('span');
  span.className('box');
  document.body.appendChild(span);
});


5. xpath knihovna s atributem rok kde hodnota roku je 2022
- //knihovna[@rok='2022']




# 10:45
1. vsechny casti url a jejich priklad + vysvetlit
https://www.example.com:443/products/shoes?search=running+shoes&category=sport#reviews
schema,   domena         port      cesta    dotaz                fragment

⁠2. css kde musis dat velikost textu o 20% vetsi nez nadrazeny tag a ma byt pouzitelna jen pro span s idckem ??? kdy to je v divu

div span#id {
  font-size: 120%
}


⁠3. css kdy je pozadi obrazek a cervene pismo, pri najeti ma byt pismo tluste
.back {
  background-iamge: url('path');
  color: red;
}

.back:hover {
  font-weight: bold;
}


⁠4. javascript kdy pri odeslani formu musis checknout jestli input s idckem jmeno neni prazdny, pokud je tak vyhodit alert

document.querrySelector('form').addEventListener('submit', function(e){
  var nameInput = document.getElementById('jmeno');
  if (nameInput.value.trim() === ''){
    alert('Jmeno nesmi byt prazdne');
    e.precentDefault();
  }
})

⁠5. vyselectit textove hodnoty z xpath moznosti
//element/text()


# 11:15
1. Co typicky obsahuje http response a napište a popište skupiny response kódu

2. Napište css pro obrázek, který bude mít červenou border a nemá identifikator a nachází se v nějakém elementů (byl specifikovaný) s třídou obrazec

.obrazec img {
    border: 2px solid red;
}

3. Napište css pro první li, kdy bude text modrý a bude uvnitř ul s zase nějakou specifikovanou třídou
.class1 ul li:first-child{
  color: blue;
}

4. Napište JS kdy máte obrázek s src menu.png a když na něho najedete tak se jeho src změní na menu-on.png po vyjetí se změní zpátky na původní obrázek.

var img = document.querySelector('img[src="menu.png"]');

img.addEventListener('mouseenter', function() {
    this.src = 'menu-on.png';
});

img.addEventListener('mouseleave', function() {
    this.src = 'menu.png';
});

5. Xpath na nalezení všech elementů  možnost s hlas větší než 10
//možnost[@hlas > 10]