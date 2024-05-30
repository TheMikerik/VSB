package ruc0066.java2.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ruc0066.java2.model.Survey;
import ruc0066.java2.repository.SurveyRepository;

import java.util.List;

@Service
public class SurveyServiceImpl implements SurveyService {

    @Autowired
    private SurveyRepository surveyRepository;

    @Override
    public Survey saveSurvey(Survey survey) {
        return surveyRepository.save(survey);
    }

    @Override
    public List<Survey> getAllSurveys() {
        return surveyRepository.findAll();
    }

    @Override
    public Survey getSurveyById(int surveyId) {
        return surveyRepository.findById(surveyId).orElse(null);
    }
}
