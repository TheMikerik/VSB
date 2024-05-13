package ruc0066.java2.service;

import org.springframework.stereotype.Service;
import ruc0066.java2.model.Survey;

import java.util.List;

public interface SurveyService {
    public Survey saveSurvey(Survey survey);
    public List<Survey> getAllSurveys();
    public Survey getSurveyById(int surveyId);
}
