import QuestionInt from "./_question";

interface SurveyInt {
  id: number;
  title: string;
  description: string;
  estimatedTime: string;
  questions: QuestionInt[];
}

export default SurveyInt;