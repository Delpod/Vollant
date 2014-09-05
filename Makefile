.PHONY: clean All

All:
	@echo "----------Building project:[ Vollant - Release ]----------"
	@$(MAKE) -f  "Vollant.mk"
clean:
	@echo "----------Cleaning project:[ Vollant - Release ]----------"
	@$(MAKE) -f  "Vollant.mk" clean
