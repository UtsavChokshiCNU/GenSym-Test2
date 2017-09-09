import java.io.*;
import java.nio.channels.FileChannel;
import java.util.Calendar;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Updates version numbers for the Gensym release
 */
public class UpdateGensymVersion {
    private static final String RELEASE_LEVEL_PROTOTYPE = "8";
    private static final String RELEASE_LEVEL_ALPHA = "16";
    private static final String RELEASE_LEVEL_BETA = "32";
    private static final String RELEASE_LEVEL_PATCH = "64";
    private static final String RELEASE_LEVEL_CRELEASE = "128";

    /** The version of G2 in "four-number-format".  First number is
	the external version number, second the minor (release)
	version number, third the "release level" (alpha, beta,
	final...) and the fourth is the "iterator within the release
	level".
	@todo update automatically or store into a text file 
     */
    private static final String fileVersion = "2015,20,32,0";

    /**
     * The letters are A=Jan, B=Feb, C=Mar, D=Apr, E=May,
     * F=Jun, G=Jul, H=Aug, I=Sep, J=Oct, K=Nov, and L=Dec.
     */
    private static final String MONTH_CODES = "ABCDEFGHIJKL";

    /** Year code: A->1998, B->1999, ..., N->2011, ..., 9->2033. */
    private static final String YEAR_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    private static final String[] MONTH_NUMBERS =
        new String[]{"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

    private final Pattern DELTA_LISP_BUILD_ID_PATTERN = Pattern.compile("(^.*build-identification-string \").+(\".*$)");
    private final Pattern DELTA_LISP_BUILD_COMMENT_PATTERN = Pattern.compile("(^.*build-comment-string \").+(\".*$)");
    private final Pattern DELTA_LISP_revision_number = Pattern.compile("(^\\(.*revision-number-of-current-gensym-product-line ).+(\\).*$)");
    private final Pattern DELTA_LISP_release_quality = Pattern.compile("(^\\(.*release-quality-of-current-gensym-product-line ).+(\\).*$)");

    private final Pattern RC_BUILD_ID_PATTERN = Pattern.compile("(^ *VALUE \"Build ID\", \")....(\\\\0\".*$)");
    private final Pattern G2DB_BUILD_ID_PATTERN = Pattern.compile("(^.*BUILD_CODE \").+(\".*$)");
    private final Pattern FILE_VERSION_PATTERN = Pattern.compile("(^.*FILEVERSION ).+$");
    private final Pattern PRODUCT_VERSION_PATTERN = Pattern.compile("(^.*PRODUCTVERSION ).+$");

    private final Pattern ASCIIDOC_VERSION_PATTERN = Pattern.compile("(^:revnumber: ).+$");
    private final Pattern ASCIIDOC_REVDATE_PATTERN = Pattern.compile("(^:revdate: ).+$");

    private String buildId;
    private String buildComment;

    private String makeBuildComment(Calendar calendar) {
        String result = String.valueOf(calendar.get(Calendar.YEAR)) + "." + MONTH_NUMBERS[calendar.get(Calendar.MONTH)];
	String[] parts = fileVersion.split(",");
	if (RELEASE_LEVEL_BETA.equals(parts[2])) {
	    result += ".W" + parts[3];
	}
	return result;
    }

    private void updateVersionFiles() throws IOException {
        File srcBox = new File("..");

        Calendar calendar = Calendar.getInstance();
        char yearCode = YEAR_CODES.charAt((calendar.get(Calendar.YEAR) - 1998) % 26);
        char monthCode = MONTH_CODES.charAt(calendar.get(Calendar.MONTH));
        int day = calendar.get(Calendar.DAY_OF_MONTH);
        buildId = String.format("%c%c%s", yearCode, monthCode, day < 10 ? "0" + day : String.valueOf(day));
	buildComment = makeBuildComment(calendar);

	String[] parts = fileVersion.split(",");
	final String officialVersion = "Gensym." + parts[0] + "." + parts[1];
	final String revdate = calendar.getDisplayName(Calendar.MONTH, Calendar.LONG, java.util.Locale.US) + " " + calendar.get(Calendar.YEAR);

        updateDeltaLispFile(new File(srcBox, "lisp/delta.lisp"));
        updateRcFile(new File(srcBox, "g2/c/g2.rc"));
        updateRcFile(new File(srcBox, "ext/c/g2pwd.rc"));
        updateRcFile(new File(srcBox, "tw/c/tw.rc"));
        updateRcFile(new File(srcBox, "gsi/c/gsi.rc"));
        updateRcFile(new File(srcBox, "gw/c/gw.rc"));
        updateRcFile(new File(srcBox, "twng/c/Twng.rc"));
        updateRcFile(new File(srcBox, "activex/G2Com/G2Com.rc"));
        updateRcFile(new File(srcBox, "activex/control/src/resources.rc"));
        updateRcFile(new File(srcBox, "activex/control/wsview/view-resources.rc"));
        updateRcFile(new File(srcBox, "g2i/TwOCX/TelewindowsAx.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2-ora10.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2-ora11.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2-ora12.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2odbc.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2sqlsvr.rc"));
        updateRcFile(new File(srcBox, "g2db/c/g2-syb150.rc"));
        updateRcFile(new File(srcBox, "corba/cpp/g2corba.rc"));
        updateRcFile(new File(srcBox, "g2opc/cpp/opclink.rc"));
        updateRcFile(new File(srcBox, "g2pi/c/g2pi.rc"));
        updateRcFile(new File(srcBox, "gservice/c/gservice.rc"));
        updateRcFile(new File(srcBox, "g2i/sites/HLA/bridge_src/G2_HLA.rc"));
        updateG2DBHeaderFile(new File(srcBox, "g2db/c/build_code.h"));
	updateAsciidocFile(new File(srcBox, "documentation/asciidoc/g2javasocketmanager.adoc"), officialVersion, revdate);
	updateAsciidocFile(new File(srcBox, "documentation/asciidoc/g2langrefcard.adoc"), officialVersion, revdate);
    }

    public static String releaseQualityFromFileVersion(final String fileVersion) {
	String relev = fileVersion.split(",")[2];
	if (RELEASE_LEVEL_PROTOTYPE.equals(relev)) {
	    return "prototype-release-quality";
	}
	else if (RELEASE_LEVEL_ALPHA.equals(relev)) {
	    return "alpha-release-quality";
	}
	else if (RELEASE_LEVEL_BETA.equals(relev)) {
	    return "beta-release-quality";
	}
	else if (RELEASE_LEVEL_PATCH.equals(relev)) {
	    System.err.println("G2 Lisp actually doesn't support the patch release level set for: " + fileVersion);
	    return "release-quality";
	}
	else if (RELEASE_LEVEL_CRELEASE.equals(relev)) {
	    return "release-quality";
	}
	else {
	    System.err.println("Uknown release level for file-version: " + fileVersion);
	    return "prototype-release-quality";
	}
    }

    /**
     * Updates 'build-identification-string', 'build-comment-string',
     * 'revision-number-of-current-gensym-product-line' and
     * 'release-quality-of-current-gensym-product-line` in
     * src/lisp/delta.lisp
     *
     * @param srcFile delta.lisp file
     */
    private void updateDeltaLispFile(final File srcFile) throws IOException {
        File acopy = copyFile(srcFile);
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(acopy)));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(srcFile)));
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher idMatch = DELTA_LISP_BUILD_ID_PATTERN.matcher(line);
                Matcher commentMatch = DELTA_LISP_BUILD_COMMENT_PATTERN.matcher(line);
                Matcher revisionMatch = DELTA_LISP_revision_number.matcher(line);
                Matcher releaseqMatch = DELTA_LISP_release_quality.matcher(line);
                if (idMatch.matches()) {
                    writer.write(idMatch.group(1));
                    writer.write(buildId);
                    writer.write(idMatch.group(2));
                } else if (commentMatch.matches()) {
                    writer.write(commentMatch.group(1));
                    writer.write(buildComment);
                    writer.write(commentMatch.group(2));
                } else if (revisionMatch.matches()) {
                    writer.write(revisionMatch.group(1));
                    writer.write(fileVersion.split(",")[1]);
                    writer.write(revisionMatch.group(2));
                } else if (releaseqMatch.matches()) {
                    writer.write(releaseqMatch.group(1));
                    writer.write(releaseQualityFromFileVersion(fileVersion));
                    writer.write(releaseqMatch.group(2));
		}
		else {
                    writer.write(line);
                }
                writer.write("\n");
            }
        } finally {
            closeQuietly(reader);
            closeQuietly(writer);
            acopy.delete();
        }
    }

    private void updateG2DBHeaderFile(final File srcFile) throws IOException {
        File acopy = copyFile(srcFile);
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(acopy)));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(srcFile)));
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher idMatch = G2DB_BUILD_ID_PATTERN.matcher(line);
                if (idMatch.matches()) {
                    writer.write(idMatch.group(1));
                    writer.write(buildId);
                    writer.write(idMatch.group(2));
                } else {
                    writer.write(line);
                }
                writer.write("\n");
            }
        } finally {
            closeQuietly(reader);
            closeQuietly(writer);
            acopy.delete();
        }
    }


    /**
     * Updates the given .rc file (g2.rc, tw.rc, twng.rc)
     *
     * @param srcFile .rc file
     */
    private void updateRcFile(final File srcFile) throws IOException {
        File acopy = copyFile(srcFile);
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(acopy)));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(srcFile)));
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher matcher = RC_BUILD_ID_PATTERN.matcher(line);
                Matcher matcher2 = FILE_VERSION_PATTERN.matcher(line);
                Matcher matcher3 = PRODUCT_VERSION_PATTERN.matcher(line);

                if (matcher.matches()) {
                    writer.write(matcher.group(1));
                    writer.write(buildId);
                    writer.write(matcher.group(2));
                } else if (matcher2.matches()) {
                    writer.write(matcher2.group(1));
                    writer.write("   ");
                    writer.write(fileVersion);
                } else if (matcher3.matches()) {
                    writer.write(matcher3.group(1));
                    writer.write(fileVersion);
                } else {
                    writer.write(line);
                }
                writer.write("\r\n");
            }
        } finally {
            closeQuietly(reader);
            closeQuietly(writer);
            acopy.delete();
        }
    }

    /**
     * Updates the given .adoc file - Asciidoc documentation
     *
     * @param srcFile the `.adoc` file to update
     */
    private void updateAsciidocFile(final File srcFile, final String officialVersion, final String revdate) throws IOException {
        File acopy = copyFile(srcFile);
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(acopy)));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(srcFile)));
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher vermatch = ASCIIDOC_VERSION_PATTERN.matcher(line);
                Matcher revdatematch = ASCIIDOC_REVDATE_PATTERN.matcher(line);

                if (vermatch.matches()) {
                    writer.write(vermatch.group(1));
                    writer.write(officialVersion);
		}
                else if (revdatematch.matches()) {
                    writer.write(revdatematch.group(1));
                    writer.write(revdate);
		}
		else {
                    writer.write(line);
                }
                writer.write("\n");
            }
        } finally {
            closeQuietly(reader);
            closeQuietly(writer);
            acopy.delete();
        }
    }

    /**
     * Copy the given file
     *
     * @param srcFile file to be copied
     *
     * @return the result file
     */
    private File copyFile(final File srcFile) throws IOException {
        File destFile = File.createTempFile("gensym_", null);

        FileInputStream fis = null;
        FileOutputStream fos = null;
        FileChannel input = null;
        FileChannel output = null;
        try {
            fis = new FileInputStream(srcFile);
            fos = new FileOutputStream(destFile);
            input = fis.getChannel();
            output = fos.getChannel();
            long size = input.size();
            long pos = 0;
            while (pos < size) {
                pos += output.transferFrom(input, pos, size - pos);
            }
        } finally {
            closeQuietly(output);
            closeQuietly(fos);
            closeQuietly(input);
            closeQuietly(fis);
        }

        if (srcFile.length() != destFile.length()) {
            throw new IOException("Failed to copy full contents from '" + srcFile + "' to '" + destFile + "'");
        }

        return destFile;
    }

    /**
     * Unconditionally close a <code>Closeable</code>.
     *
     * @param closeable the object to close, may be null or already closed
     */
    public static void closeQuietly(Closeable closeable) {
        try {
            if (closeable != null) {
                closeable.close();
            }
        } catch (IOException ioe) {
            // ignore
        }
    }

    public static void main(String[] args) throws IOException {
        UpdateGensymVersion worker = new UpdateGensymVersion();
        worker.updateVersionFiles();
    }
}
