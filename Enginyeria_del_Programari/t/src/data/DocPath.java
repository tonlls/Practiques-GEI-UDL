package data;

final public class DocPath {
    private final String path;

    public DocPath(String path) throws NullDocPathException, NotValidDocPathException {
        //check if path is valid and not null
        if (path == null) throw new NullDocPathException("path is null");
        if (!isValid(path)) throw new NotValidDocPathException("path is invalid");
        this.path = path;
    }

    private boolean isValid(String path) {
        //check if path is valid
        if (path.length() == 0) return false;
        return true;
    }

    public String getPath() {return path;}

    public boolean equals(Object o) {
        if (o instanceof DocPath) {
            return path.equals(((DocPath) o).getPath());
        }
        return false;
    }

    public int hashCode() {return path.hashCode();}

    @Override
    public String toString() {
        return "DocPath{ path='"+path+"'}";
    }
}
