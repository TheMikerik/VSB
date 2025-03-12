package ruc0066.java2.service;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ruc0066.java2.model.Option;
import ruc0066.java2.model.Questions;
import ruc0066.java2.repository.OptionRepository;
import ruc0066.java2.repository.QuestionsRepository;
import java.util.List;

@Service
public class OptionServiceImpl implements OptionService {

    @Autowired
    private OptionRepository optionRepository;

    @Autowired
    private QuestionsRepository questionsRepository;

    @PersistenceContext
    private EntityManager entityManager;

    @Override
    public Option saveOption(Option option) {
        return optionRepository.save(option);
    }

    public List<Option> getAllOption(int questionId) {
        return entityManager.createQuery(
                "SELECT o FROM Option o WHERE o.questions.id = :questionId", Option.class)
                .setParameter("questionId", questionId)
                .getResultList();
    }

    @Override
    public Questions getQuestionById(int questionId) {
        return questionsRepository.findById(questionId).orElse(null);
    }
}
