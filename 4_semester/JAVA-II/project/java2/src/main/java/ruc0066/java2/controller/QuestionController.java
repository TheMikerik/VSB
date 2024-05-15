package ruc0066.java2.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ruc0066.java2.model.Questions;
import ruc0066.java2.model.Survey;
import ruc0066.java2.service.QuestionsService;

import java.util.List;

@RestController
@RequestMapping("/api/questions")
@CrossOrigin
public class QuestionController {
    @Autowired
    private QuestionsService questionsService;

    @PostMapping("/add/{surveyId}")
    public String add(@PathVariable int surveyId, @RequestBody Questions questions) {
        try {
            if (questions != null) {
                Survey survey = questionsService.getSurveyById(surveyId);
                if (survey != null) {
                    questions.setSurvey(survey);
                    questionsService.saveQuestions(questions);
                    return "Question added successfully";
                } else {
                    return "Failed to add question: Survey with ID " + surveyId + " not found";
                }
            } else {
                return "Failed to add question: Invalid data provided";
            }
        } catch (Exception e) {
            return "Failed to add question: " + e.getMessage();
        }
    }


    @GetMapping("/getAll/{surveyId}")
    public List<Questions> getAllQuestions(@PathVariable int surveyId) {
        return questionsService.getAllQuestions(surveyId);

    }
}
