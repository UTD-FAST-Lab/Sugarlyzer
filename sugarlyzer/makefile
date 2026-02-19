

build: build_dispatcher build_tester build_tester_test

build_dispatcher:
	@echo "Building Dispatcher JAR"
	sbt "dispatcher/assembly"

build_tester:
	@echo "Building Tester JAR"
	sbt "tester/assembly"

build_tester_test:
  @echo "Building Tester test JAR"
	sbt "tester_test/assembly"

clean:
	rm -rf dispatcher.jar tester.jar tester_test.jar
