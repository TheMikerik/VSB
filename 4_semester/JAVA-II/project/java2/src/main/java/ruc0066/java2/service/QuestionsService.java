package ruc0066.java2.service;

import ruc0066.java2.model.Questions;
import ruc0066.java2.model.Survey;
import java.util.List;

public interface QuestionsService {
    public Questions saveQuestions(Questions questions);
    public List<Questions> getAllQuestions(int surveyId);

    public Survey getSurveyById(int surveyId);
}
