package ruc0066.java2.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import ruc0066.java2.model.Option;
import ruc0066.java2.model.Questions;
import ruc0066.java2.service.OptionService;
import java.util.List;

@RestController
@RequestMapping("/api/option")
@CrossOrigin
public class OptionController {
    @Autowired
    private OptionService optionService;

    @PostMapping("/add/{questionID}")
    public String add(@PathVariable int questionID, @RequestBody Option option) {
        try {
            if (option != null) {
                Questions question = optionService.getQuestionById(questionID);
                if (question != null) {
                    option.setQuestions(question);
                    optionService.saveOption(option);
                    return "Option added successfully";
                } else {
                    return "Failed to add option: Question with ID " + questionID + " not found";
                }
            } else {
                return "Failed to add option: Invalid data provided";
            }
        } catch (Exception e) {
            return "Failed to add option: " + e.getMessage();
        }
    }


    @GetMapping("/getAll/{questionID}")
    public List<Option> getAllOption(@PathVariable int questionID) {
        return optionService.getAllOption(questionID);

    }
}
