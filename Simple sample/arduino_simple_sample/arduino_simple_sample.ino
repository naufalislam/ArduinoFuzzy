#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  FuzzyInput *distance = new FuzzyInput(1);
  FuzzySet *small = new FuzzySet(0, 20, 20, 40);
  distance->addFuzzySet(small);
  FuzzySet *safe = new FuzzySet(30, 50, 50, 70);
  distance->addFuzzySet(safe);
  FuzzySet *big = new FuzzySet(60, 80, 80, 80);
  distance->addFuzzySet(big);
  fuzzy->addFuzzyInput(distance);


  FuzzyOutput *speed = new FuzzyOutput(1);
  FuzzySet *slow = new FuzzySet(0, 10, 10, 20);
  speed->addFuzzySet(slow);
  FuzzySet *average = new FuzzySet(10, 20, 30, 40);
  speed->addFuzzySet(average);
  FuzzySet *fast = new FuzzySet(30, 40, 40, 50);
  speed->addFuzzySet(fast);
  fuzzy->addFuzzyOutput(speed);





  FuzzyRuleAntecedent *ifDistanceSmall = new FuzzyRuleAntecedent();
  ifDistanceSmall->joinSingle(small);
  FuzzyRuleConsequent *thenSpeedSlow = new FuzzyRuleConsequent();
  thenSpeedSlow->addOutput(slow);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenSpeedSlow);
  fuzzy->addFuzzyRule(fuzzyRule01);


  FuzzyRuleAntecedent *ifDistanceSafe = new FuzzyRuleAntecedent();
  ifDistanceSafe->joinSingle(safe);
  FuzzyRuleConsequent *thenSpeedAverage = new FuzzyRuleConsequent();
  thenSpeedAverage->addOutput(average);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenSpeedAverage);
  fuzzy->addFuzzyRule(fuzzyRule02);


  FuzzyRuleAntecedent *ifDistanceBig = new FuzzyRuleAntecedent();
  ifDistanceBig->joinSingle(big);
  FuzzyRuleConsequent *thenSpeedFast = new FuzzyRuleConsequent();
  thenSpeedFast->addOutput(fast);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenSpeedFast);
  fuzzy->addFuzzyRule(fuzzyRule03);
}



void loop()
{
  int input = random(0, 80);
  Serial.println("\n\n\nEntrance: ");
  Serial.print("\t\t\tDistance: ");
  Serial.println(input);
  fuzzy->setInput(1, input);
  fuzzy->fuzzify();
  float output = fuzzy->defuzzify(1);
  Serial.println("Result: ");
  Serial.print("\t\t\tSpeed: ");
  Serial.println(output);
  delay(10000);
}
