package ruc0066.java2.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ruc0066.java2.model.Survey;

@Repository
public interface SurveyRepository extends JpaRepository<Survey, Integer> {
}
