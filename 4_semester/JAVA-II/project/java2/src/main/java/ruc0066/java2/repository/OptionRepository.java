package ruc0066.java2.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ruc0066.java2.model.Option;

@Repository
public interface OptionRepository extends JpaRepository<Option, Integer>{
}
