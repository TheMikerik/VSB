README

   SIR-Generator is a C-lang project that  creates  a .SVG graph out of .CSV file.
   Final graph consist 6 linear lines, wheres 3 of them are real data from user's
   input and other 3 are SIR  data, that has been  calculated  from first line of
   initial input. This  project  compares  the  real  pandemy  situation and  the
   calculated prediction of tolerable development of it.

HOW TO RUN IT

   First of all there is a need to to confirm that the adress sanitizer is OK. You
   can confirm it by the command:
   
   
      	gcc -g -fsanitize=address SIR_generator.c -o SIR-Generator
   
   
   This command create executable file "SIR-Generator." This is the final program
   that can be executed via this command (has to have the same syntax as shown):
   
   
   	./SIR-Generator <input> <infectious_days> <infectious> <output>
   
        <input>         Input file has to be in .CSV (spreaded by ;) as excel output.
   <infectious_days>    Insted of <infectious_days> input number in INTIGER form.
      <infectious>      Insted of  <infectious>  write number in FLOAT form.
        <output>        Output file is classical .HTML or .SVG file.
    
   So for example you can use this exact command:
   
   	./SIR-Generator input.csv 8 0.3 output_test_1.html
   
CONTRIBUTING

   All  suggestions are  welcome. For major  changes, please, contact me  first  to
   discuss about it.
   
CONTACT
	
   Name:	Michal Ručka   
   Email:	ruc0066@vsb.cz
   Web: 	---
   Phone:	---

ADDITIONAL INFO

   Created 3.1.2023
   by RUC0066
