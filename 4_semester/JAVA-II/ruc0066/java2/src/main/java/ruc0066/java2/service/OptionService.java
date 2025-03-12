package ruc0066.java2.service;

import ruc0066.java2.model.Option;
import ruc0066.java2.model.Questions;
import java.util.List;

public interface OptionService {
    public Option saveOption(Option option);
    public List<Option> getAllOption(int questionId);

    public Questions getQuestionById(int questionId);
}
