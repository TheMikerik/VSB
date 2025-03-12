package ruc0066.java2.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ruc0066.java2.model.Survey;
import ruc0066.java2.service.SurveyService;

import java.util.List;

@RestController
@RequestMapping("/api/survey")
@CrossOrigin
public class SurveyController {

    @Autowired
    private SurveyService surveyService;

    @PostMapping("/add")
    public String addSurvey(@RequestBody Survey survey) {
        surveyService.saveSurvey(survey);
        return "Survey added successfully";
    }

    @GetMapping("/getAll")
    public List<Survey> getAllSurveys() {
        return surveyService.getAllSurveys();
    }

    @GetMapping("/get/{surveyId}")
    public Survey getSurveyById(@PathVariable int surveyId) {
        return surveyService.getSurveyById(surveyId);
    }
}
