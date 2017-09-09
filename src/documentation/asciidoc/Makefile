all: g2javasocketmanager.pdf g2javasocketmanager.html g2langrefcard.pdf


g2javasocketmanager.pdf: g2javasocketmanager.adoc common_preamble.adoc conventions.adoc related_documentation.adoc customer_support_services.adoc g2-doc-theme.yml
	asciidoctor-pdf -a pdf-style=g2-doc-theme.yml g2javasocketmanager.adoc

g2javasocketmanager.html: g2javasocketmanager.adoc common_preamble.adoc  conventions.adoc related_documentation.adoc customer_support_services.adoc g2-doc-theme.yml
	asciidoctor g2javasocketmanager.adoc

g2langrefcard.pdf: g2langrefcard.adoc common_preamble.adoc g2-doc-theme.yml
	asciidoctor-pdf -a pdf-style=g2-doc-theme.yml g2langrefcard.adoc
