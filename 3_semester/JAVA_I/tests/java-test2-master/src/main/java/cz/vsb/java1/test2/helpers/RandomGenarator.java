package cz.vsb.java1.test2.helpers;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class RandomGenarator {

	public static final Random random = new Random();

	public static final List<String> NAMES = Collections.unmodifiableList(Arrays.asList("Abigail", "Adam", "Ada",
			"Adolf", "Adéla", "Adrián", "Adela", "Adrian", "Adina", "Aladár", "Adriána", "Alan", "Adriana", "Albert",
			"Adriena", "Albín", "Agata", "Aleš", "Agáta", "Alex", "Agnes", "Alexander", "Agnesa", "Alexandr", "Agneša",
			"Alexej", "Albína", "Alfons", "Alena", "Alfred", "Alenka", "Alfréd", "Alexandra", "Alois", "Alica", "Alojz",
			"Alice", "Anatolij", "Alina", "André", "Alla", "Andreas", "Alma", "Andrej", "Aloisie", "Andrzej", "Alžbeta",
			"Anthony", "Alžběta", "Anton", "Amália", "Antonie", "Amalie", "Antonín", "Amálie", "Antonio", "Amanda",
			"Arnold", "Amelie", "Arnošt", "Amélie", "Arpád", "Amy", "Artur", "Anastasie", "Attila", "Anastázia",
			"Augustín", "Anastázie", "Augustin", "Anastazie", "Barnabáš", "Anděla", "Bartolomej", "Andrea",
			"Bartoloměj", "Aneta", "Bedřich", "Anetta", "Benedikt", "Anežka", "Benjamín", "Angela", "Benjamin",
			"Angelika", "Bernard", "Angelina", "Blahoslav", "Anika", "Blažej", "Anita", "Bogdan", "Anna", "Bohdan",
			"Anna Marie", "Bohumil", "Anna-Marie", "Bohumír", "Annelies", "Bohuš", "Annemarie", "Bohuslav", "Antonia",
			"Boleslav", "Antónia", "Borek", "Antonína", "Bořek", "Apolena", "Boris", "Aranka", "Bořivoj", "Arnoštka",
			"Božetěch", "Augusta", "Branislav", "Augustina", "Břetislav", "Aurelie", "Brian", "Bára", "Bronislav",
			"Barbara", "Bruno", "Barbora", "Čeněk", "Beáta", "Česlav", "Beata", "Čestmír", "Beatrice", "Christian",
			"Bedřiška", "Christopher", "Běla", "Ctibor", "Berenika", "Ctirad", "Berta", "Cyril", "Bianka", "Dalibor",
			"Bibiana", "Dalimil", "Blahoslava", "Damian", "Blanka", "Damián", "Blažena", "Dan", "Bohdana", "Daniel",
			"Bohumila", "Darek", "Bohumíra", "David", "Bohunka", "Dávid", "Bohuslava", "Denis", "Božena", "Dennis",
			"Brigita", "Dezider", "Brigitta", "Diego", "Bronislava", "Dieter", "Carmen", "Dimitrij", "Carolina",
			"Dobromil", "Caroline", "Dobroslav", "Cecília", "Dominik", "Cecilie", "Drahomír", "Cecílie", "Drahoslav",
			"Charlota", "Dušan", "Charlotta", "Edmund", "Charlotte", "Eduard", "Chiara", "Edvard", "Christa", "Egon",
			"Christina", "Elemír", "Christine", "Eliáš", "Claudia", "Emanuel", "Claudie", "Emerich", "Dagmar", "Emil",
			"Dagmara", "Erhard", "Dana", "Eric", "Danica", "Erich", "Daniela", "Erik", "Danka", "Ernest", "Danny",
			"Ervin", "Danuše", "Ervín", "Danuška", "Eugen", "Danuta", "Evald", "Daria", "Evžen", "Darina", "Fabián",
			"Darja", "Fabian", "Dáša", "Fedor", "Daša", "Felix", "Debora", "Ferdinand", "Denisa", "Filip", "Diana",
			"Florián", "Dita", "Florian", "Dobromila", "František", "Dobroslava", "Gabriel", "Dominika", "Gejza",
			"Dora", "George", "Doris", "Georgios", "Dorota", "Gerhard", "Dorothea", "Gražyna", "Doubravka", "Günter",
			"Drahomíra", "Gűnter", "Drahoslava", "Gustav", "Drahuše", "Hanuš", "Drahuška", "Heinz", "Dušana", "Helmut",
			"Edeltraud", "Henryk", "Edeltrauda", "Herbert", "Edeltruda", "Heřman", "Edita", "Horst", "Edith", "Horymír",
			"Ela", "Hubert", "Elen", "Hugo", "Elena", "Hynek", "Eleni", "Ignác", "Eleonora", "Igor", "Elfrída", "Ilja",
			"Elfrieda", "Imrich", "Elisa", "Ivan", "Elisabeth", "Ivo", "Eliška", "Ivoš", "Elizabeth", "Jáchym", "Ella",
			"Jakub", "Ellen", "Jakub Jan", "Elsa", "Jan", "Elvíra", "Ján", "Ema", "Janusz", "Emanuela", "Jarmil",
			"Emília", "Jarolím", "Emilia", "Jaromír", "Emílie", "Jaroslav", "Emilie", "Jasmin", "Emily", "Jeroným",
			"Emma", "Jiljí", "Erika", "Jindra", "Erna", "Jindřich", "Ester", "Jiří", "Estera", "Johan", "Etela", "John",
			"Eugenie", "Jonáš", "Eva", "Jonatan", "Evelina", "Josef", "Evelína", "Jozef", "Evžena", "Julian", "Evženie",
			"Julius", "Filomena", "Július", "Františka", "Juraj", "Gabriela", "Jurij", "Galina", "Justin", "Gerda",
			"Kamil", "Gerlinda", "Karel", "Gerta", "Karol", "Gertruda", "Kazimír", "Gisela", "Kevin", "Gita", "Klaus",
			"Gizela", "Klement", "Greta", "Koloman", "Gréta", "Konrád", "Halina", "Konstantin", "Halka", "Kristián",
			"Hana", "Kristian", "Hanička", "Kryštof", "Hanka", "Kurt", "Hanna", "Květoslav", "Hannelore", "Kvido",
			"Heda", "Ladislav", "Hedviga", "Leo", "Hedvika", "Leon", "Helena", "Leonard", "Helga", "Leopold",
			"Henrieta", "Leoš", "Hermína", "Lešek", "Hermina", "Lev", "Herta", "Libor", "Hilda", "Lubomír", "Hildegard",
			"Ľubomír", "Hildegarda", "Lubor", "Ida", "Ľuboš", "Ilona", "Luboš", "Ilonka", "Lucas", "Ilsa", "Luděk",
			"Ilse", "Ludevít", "Ina", "Ludovít", "Inge", "Ľudovit", "Ingeborg", "Ľudovít", "Ingrid", "Ludvík", "Inka",
			"Lukáš", "Inna", "Lukas", "Irena", "Lumír", "Irina", "Manfred", "Irma", "Marcel", "Irmgard", "Marco",
			"Isabel", "Marcus", "Isabela", "Marek", "Isabella", "Marian", "Iva", "Marián", "Ivana", "Mario", "Ivanka",
			"Mário", "Iveta", "Mark", "Ivona", "Marko", "Izabela", "Markus", "Jadwiga", "Maroš", "Jana", "Martin",
			"Janetta", "Matěj", "Janette", "Matej", "Janina", "Mathias", "Janis", "Matias", "Janka", "Matouš",
			"Jarmila", "Matteo", "Jaromíra", "Matthias", "Jaroslava", "Matúš", "Jaruše", "Matyáš", "Jaruška", "Matyas",
			"Jasmína", "Max", "Jelena", "Maxim", "Jena", "Maximilian", "Jenifer", "Maxmilian", "Jennifer", "Maxmilián",
			"Jenovefa", "Metoděj", "Jesika", "Michael", "Jessica", "Michail", "Jindřiška", "Michal", "Jiřina",
			"Mikoláš", "Jiřinka", "Mikuláš", "Jitka", "Milan", "Jitřenka", "Milán", "Joanna", "Miloň", "Johana",
			"Miloš", "Johanka", "Miloslav", "Johanna", "Milouš", "Jolana", "Mirek", "Jolanta", "Mirko", "Josefa",
			"Miroslav", "Josefina", "Mojmír", "Josefína", "Nicholas", "Jozefa", "Nick", "Jozefína", "Nicolas",
			"Jozefina", "Nikita", "Judita", "Nikolaj", "Júlia", "Nikolas", "Julia", "Nikos", "Juliana", "Norbert",
			"Juliána", "Oldřich", "Julie", "Oleg", "Justína", "Oliver", "Justina", "Omar", "Justýna", "Ondřej",
			"Kamila", "Ondrej", "Karen", "Oskar", "Karin", "Osvald", "Karina", "Ota", "Karla", "Otakar", "Karolina",
			"Otmar", "Karolína", "Oto", "Katarína", "Otokar", "Katarina", "Otomar", "Kateřina", "Otta", "Katka", "Otto",
			"Katrin", "Otto", "Klára", "Patrick", "Klaudia", "Patrik", "Klaudie", "Paul", "Kornelie", "Pavel", "Krista",
			"Pavol", "Kristína", "Peter", "Kristina", "Petr", "Kristýna", "Philip", "Krystyna", "Pravoslav", "Květa",
			"Přemek", "Kvetoslava", "Přemysl", "Květoslava", "Prokop", "Květuše", "Quido", "Květuška", "Radan", "Lada",
			"Radek", "Ladislava", "Radim", "Lara", "Radimír", "Larisa", "Radislav", "Laura", "Radko", "Lea", "Radomil",
			"Leila", "Radomír", "Lena", "Radoslav", "Lenka", "Radovan", "Leona", "Rafael", "Leontina", "Raimund",
			"Leontýna", "Rajmund", "Leopolda", "Rastislav", "Leopoldina", "Reinhard", "Lia", "Reinhold", "Liana",
			"René", "Liběna", "Richard", "Libuša", "Robert", "Libuše", "Róbert", "Lída", "Robin", "Lidia", "Roland",
			"Lidie", "Roman", "Lidmila", "Ronald", "Liduše", "Rostislav", "Liduška", "Rudolf", "Lilian", "Samuel",
			"Liliana", "Sebastian", "Lilien", "Sebastián", "Lilly", "Sebastien", "Linda", "Sergej", "Lívia", "Silvestr",
			"Ljuba", "Šimon", "Ljubov", "Simon", "Ľubica", "Slávek", "Ľubomíra", "Slavoj", "Lubomíra", "Slavomil",
			"Luca", "Slavomír", "Lucia", "Stanislav", "Lucie", "Štefan", "Luďka", "Stefan", "Ľudmila", "Štěpán",
			"Ludmila", "Svatomír", "Ludvika", "Svatopluk", "Luisa", "Svatoslav", "Lydia", "Tadeáš", "Lýdia", "Teodor",
			"Lydie", "Theodor", "Lýdie", "Thomas", "Madlen", "Tibor", "Magda", "Tim", "Magdalena", "Timotej",
			"Magdaléna", "Tobiáš", "Maja", "Tobias", "Mája", "Tom", "Malvína", "Tomáš", "Manuela", "Tomasz", "Marcela",
			"Tomislav", "Margareta", "Tony", "Margarita", "Václav", "Margit", "Valdemar", "Margita", "Valentin",
			"Maria", "Valérie", "Mária", "Valter", "Mariana", "Vasil", "Marianna", "Vavřinec", "Marianne", "Vendelín",
			"Marie", "Verner", "Marie Anna", "Věroslav", "Marija", "Viktor", "Marika", "Vilém", "Marina", "Viliam",
			"Markéta", "Vilibald", "Marketa", "Vincenc", "Marta", "Vincent", "Martina", "Vít", "Maruše", "Vitalij",
			"Maruška", "Vítek", "Matilda", "Vítězslav", "Matylda", "Vladan", "Maya", "Vladimír", "Melánie", "Vladimir",
			"Melanie", "Vladislav", "Melisa", "Vlastimil", "Melissa", "Vlastimír", "Mia", "Vlastislav", "Michaela",
			"Vojta", "Michala", "Vojtěch", "Michelle", "Vojtech", "Milada", "Vratislav", "Milana", "Waldemar", "Milena",
			"Walter", "Miloslava", "Waltraud", "Miluše", "Werner", "Miluška", "William", "Miriam", "Wolfgang", "Mirka",
			"Zbigniew", "Miroslava", "Zbyhněv", "Monika", "Zbyněk", "Naďa", "Zbyšek", "Naděžda", "Zdeněk", "Nadežda",
			"Zdenek", "Nancy", "Zděnek", "Natali", "Zdenko", "Natália", "Zdislav", "Natalia", "Zoltán", "Natalie",
			"Natálie", "Natalija", "Nataša", "Nathalie", "Nela", "Nella", "Nelli", "Nelly", "Nicol", "Nicola", "Nicole",
			"Nika", "Nikol", "Nikola", "Nikoleta", "Nina", "Noemi", "Nora", "Oksana", "Oldřiška", "Olena", "Oĺga",
			"Oľga", "Olga", "Olina", "Olivia", "Olivie", "Oluše", "Otilie", "Pamela", "Patricia", "Patricie", "Paula",
			"Paulína", "Paulina", "Pavla", "Pavlina", "Pavlína", "Petra", "Petronela", "Petronila", "Petruše",
			"Petruška", "Ráchel", "Radana", "Radka", "Radmila", "Radomila", "Radomíra", "Radoslava", "Radovana",
			"Rebecca", "Rebeka", "Regína", "Regina", "Renata", "Renáta", "Renée", "Ria", "Rita", "Romana", "Rosalie",
			"Rosemarie", "Rostislava", "Rozalia", "Rozália", "Rozálie", "Rozalie", "Rozárie", "Rozárka", "Rudolfa",
			"Rut", "Ruth", "Růžena", "Ružena", "Sabina", "Sabrina", "Samanta", "Samantha", "Sandra", "Sara", "Sára",
			"Sarah", "Šárka", "Šarlota", "Saša", "Silva", "Silvia", "Silvie", "Simona", "Slavěna", "Slávka",
			"Slavomila", "Slavomíra", "Sofia", "Sofie", "Sofie Anna", "Soňa", "Sonia", "Sonja", "Sophia", "Sophie",
			"Stanislava", "Štefana", "Štefania", "Štefánia", "Stefanie", "Štefanie", "Stela", "Stella", "Štěpánka",
			"Svatava", "Svatoslava", "Světla", "Světlana", "Svetlana", "Světluše", "Světluška", "Sylva", "Sylvia",
			"Sylvie", "Tamara", "Táňa", "Taťána", "Taťana", "Tatiana", "Tatjana", "Taťjana", "Tea", "Teodora", "Teresa",
			"Tereza", "Terézia", "Terezia", "Terezie", "Thea", "Theodora", "Timea", "Tina", "Uršula", "Ursula",
			"Urszula", "Václava", "Valentina", "Valentýna", "Valeria", "Valéria", "Valerie", "Vanda", "Vanesa",
			"Vanessa", "Vědunka", "Věnceslava", "Vendula", "Vendulka", "Venuše", "Věra", "Verona", "Veronica",
			"Veronika", "Věroslava", "Věruška", "Victoria", "Viera", "Viktória", "Viktoria", "Viktorie", "Viléma",
			"Vilemína", "Vilma", "Viola", "Vítězslava", "Vivien", "Vladana", "Vladěna", "Vladimíra", "Vladislava",
			"Vlasta", "Vlastimila", "Vlastislava", "Vojtěška", "Vratislava", "Wanda", "Xenie", "Yveta", "Yvetta",
			"Yvona", "Yvonna", "Yvonne", "Žaneta", "Zdena", "Zděna", "Zděnka", "Zdeňka", "Zdenka", "Zdislava", "Zina",
			"Zita", "Zlata", "Zlatica", "Zlatuše", "Zlatuška", "Zoe", "Žofia", "Zofia", "Žofie", "Zoja", "Zora",
			"Zorka", "Zuzana"));

	public static final List<String> SURNAMES = Collections.unmodifiableList(Arrays.asList("Novák", "Svoboda",
			"Novotný", "Dvořák", "Černý", "Procházka", "Kučera", "Veselý", "Horák", "Němec", "Pokorný", "Marek",
			"Pospíšil", "Hájek", "Jelínek", "Král", "Růžička", "Beneš", "Fiala", "Sedláček", "Doležal", "Zeman",
			"Nguyen", "Kolář", "Krejčí", "Navrátil", "Čermák", "Urban", "Vaněk", "Blažek", "Kříž", "Kratochvíl",
			"Kovář", "Kopecký", "Bartoš", "Vlček", "Musil", "Šimek", "Polák", "Konečný", "Malý", "Čech", "Kadlec",
			"Štěpánek", "Staněk", "Holub", "Dostál", "Soukup", "Šťastný", "Mareš", "Sýkora", "Moravec", "Tichý",
			"Valenta", "Vávra", "Matoušek", "Bláha", "Říha", "Ševčík", "Bureš", "Hruška", "Mašek", "Pavlík", "Dušek",
			"Hrubý", "Havlíček", "Janda", "Mach", "Müller", "Liška"));

	public static <T> T selectRandom(List<T> elements) {
		return elements.get(random.nextInt(elements.size()));
	}
	
	public static String generateRandomVectorName() {
		
		StringBuilder sb = new StringBuilder();
		sb.append(generateRandomUpperCaseLetter());
		sb.append(generateRandomUpperCaseLetter());
		sb.append("-");
		sb.append(String.format("%03d", random.nextInt(1000)));
		return sb.toString();
	}

	private static char generateRandomUpperCaseLetter() {
		return (char)(random.nextInt('Z'-'A')+'A');
	}
}
