/*
 * Prints table or tree.
 * 
 * Copyright (C) 2014 Ondrej Oprala <ooprala@redhat.com>
 * Copyright (C) 2014 Karel Zak <kzak@redhat.com>
 * 
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 */
#ifndef _LIBSMARTCOLS_H
#define _LIBSMARTCOLS_H

/*
 * Column flags
 */
enum {
	SCOLS_FL_TRUNC       = (1 << 0),   /* truncate fields data if necessary */
	SCOLS_FL_TREE        = (1 << 1),   /* use tree "ascii art" */
	SCOLS_FL_RIGHT	     = (1 << 2),   /* align to the right */
	SCOLS_FL_STRICTWIDTH = (1 << 3),   /* don't reduce width if column is empty */
	SCOLS_FL_NOEXTREMES  = (1 << 4),   /* ignore extreme fields when count column width*/
	SCOLS_FL_HIDDEN	     = (1 << 5),   /* maintain data, but don't print */
	SCOLS_FL_WRAP	     = (1 << 6)    /* wrap long lines to multi-line cells */
};

#endif /* _LIBSMARTCOLS_H */

