using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CommonAAR;

namespace SlaveLauncher
{
    class SlaveNaming
    {
        private Configuration _conf;
        public const String _fmt = "{0}{1:00}";

        public SlaveNaming(Configuration conf) {
            _conf = conf;
        }
        public String GetFor(int index) {
            
            Checker.Must(index <= 99, "Format "+_fmt+" allows only 2 digits.");
            Checker.Must( _conf.MinSlaveIndex() <= index && index <= _conf.MaxSlaveIndex(),
                index );
            return String.Format(_fmt, _conf.SlaveNamePrefix(), index);
        }
        public String GetJnlpUrl(int index) {
            return String.Format(_conf.JnlpUrlPrefix()+GetFor(index)+"/slave-agent.jnlp");
        }
    }
}
