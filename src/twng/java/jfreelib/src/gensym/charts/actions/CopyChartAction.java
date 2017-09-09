package gensym.charts.actions;

import gensym.charts.*;
import org.w3c.dom.Element;

import java.awt.Image;
import java.awt.Graphics2D;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.image.BufferedImage;

import java.io.IOException;

/**
 * Copy chart action: copy chart to clipboard
 */
public class CopyChartAction implements IChartAction {

    /**
     * {@inheritDoc}
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
        final Clipboard clipboard = chart.getToolkit().getSystemClipboard();
        BufferedImage img = new BufferedImage(chart.getWidth(),
                chart.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics2D g2 = img.createGraphics();
        chart.printAll(g2);

        ImageTransferable it = new ImageTransferable(img);
        clipboard.setContents(it, it);
    }

    /**
     * {@inheritDoc}
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * {@inheritDoc}
     */
    public String getName() {
        return "Copy";
    }

    /**
     * {@inheritDoc}
     */
    public boolean isChartRequired() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
    }

    /**
     * Image transferable class, used for copying to the clipboard
     */
    static public class ImageTransferable implements Transferable, ClipboardOwner {

        private Image image;

        /**
         * Constructor
         * @param img image to copy
         */
        ImageTransferable(Image img) {
            this.image = img;
        }

        /**
         * {@inheritDoc}
         */
        public DataFlavor[] getTransferDataFlavors() {
            return new DataFlavor[]{DataFlavor.imageFlavor};
        }

        /**
         * {@inheritDoc}
         */
        public boolean isDataFlavorSupported(DataFlavor flavor) {
            return DataFlavor.imageFlavor.equals(flavor);
        }

        /**
         * {@inheritDoc}
         */
        public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
            return image;
        }

        /**
         * {@inheritDoc}
         */
        public void lostOwnership(Clipboard clipboard, Transferable contents) {
        }
    }
}
