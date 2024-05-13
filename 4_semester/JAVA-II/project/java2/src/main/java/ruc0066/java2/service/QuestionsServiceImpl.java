package ruc0066.java2.service;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ruc0066.java2.model.Questions;
import ruc0066.java2.model.Survey;
import ruc0066.java2.repository.QuestionsRepository;
import ruc0066.java2.repository.SurveyRepository;

import java.util.List;

@Service
public class QuestionsServiceImpl implements QuestionsService {

    @Autowired
    private QuestionsRepository questionsRepository;

    @Autowired
    private SurveyRepository surveyRepository;

    @PersistenceContext
    private EntityManager entityManager;

    @Override
    public Questions saveQuestions(Questions questions) {
        return questionsRepository.save(questions);
    }

    @Override
    public List<Questions> getAllQuestions(int surveyId) {
        return entityManager.createQuery(
                        "SELECT q FROM Questions q JOIN FETCH q.survey s WHERE s.id = :surveyId", Questions.class)
                .setParameter("surveyId", surveyId)
                .getResultList();
    }


    @Override
    public Survey getSurveyById(int surveyId) {
        return surveyRepository.findById(surveyId).orElse(null);
    }
}
