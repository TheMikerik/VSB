import OptionInt from "./_option";

interface QuestionInt {
  id: number;
  type: string;
  label: string;
  options: OptionInt[];
}

export default QuestionInt;