APPNAME = cnetcheck

include $(ISISROOT)/make/isismake.tsts

commands:
	$(LS) $(INPUT)/*.cub > $(OUTPUT)/list.lis;
	$(APPNAME) fromlist=$(OUTPUT)/list.lis prefix=$(OUTPUT)/cat \
	nocube=false lowcoverage=false \
	cnet=$(INPUT)/NearSide_All.net | grep -v "Processed" \
	> $(OUTPUT)/output.txt;
	$(RM) $(OUTPUT)/list.lis;
	$(RM) $(OUTPUT)/catIsland.*

	# Remove absolute paths from cube filenames, as they change depending
	# upon where the test is run from
	for i in $(OUTPUT)/*.txt; do \
	  base=`basename $$i`; \
	  cat $$i | sed 's/.*\/\(.*\.cub\)/\1/g' > $$base; \
	  $(MV) $$base $$i; \
	done
