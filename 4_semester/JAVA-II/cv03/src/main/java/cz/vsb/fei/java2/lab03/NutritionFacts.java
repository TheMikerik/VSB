package cz.vsb.fei.java2.lab03;

import lombok.Builder;

@Builder
public class NutritionFacts {
	private final int servingSize;// (mL)required
	private final int servings;// (per container) required
	private final int calories;// (per serving)optional
	private final int fat;// (g/serving)optional
	private final int sodium;// (mg/serving)optional
	private final int carbohydrate; // (g/serving) optional
}


